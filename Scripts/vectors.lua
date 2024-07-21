local first_vector = vec2.new(1.0, 5.0)
local second_vector = vec2.new(2.0, 4.0)

print("The first vector is: ")
first_vector:display()

print("The second vector is: ")
second_vector:display()

-- Testing addition
print("Adding them")
local sum = first_vector + second_vector
sum:display()

--Testing substraction
print("Subtracting them")
local diff = first_vector - second_vector
diff:display()

print("Multiplying the first one by a scalar (3)")
local scaled = first_vector * 3.0
scaled:display()

print("Testing equality, should be negative of course")
print(first_vector == second_vector)

print("Getting the magnitude of the second vector")
print(second_vector:magnitude())

print("Demonstrating the copy constructor")
local third_vector = vec2.new(first_vector)
print("A third vector has been created and has been set to the value of the first vector")
first_vector:display()
third_vector:display()
print("Now I change the Y coordinate of the third vector and it shouldn't change the first, because they're two different objects")
third_vector.y = -12.0
first_vector:display()
third_vector:display()

print("Calculating the angle between the two vectors by normalizing them, then getting their dot product")
first_vector:normalize()
second_vector:normalize()
local dotprod = first_vector:dot(second_vector)
local angle_deg = math.deg(math.acos(dotprod))
print(angle_deg)

